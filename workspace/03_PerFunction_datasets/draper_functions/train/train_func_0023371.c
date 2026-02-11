fullpacket(LIBSSH2_SESSION * session, int encrypted  )
{
    unsigned char macbuf[MAX_MACSIZE];
    struct transportpacket *p = &session->packet;
    int rc;
    int compressed;

    if (session->fullpacket_state == libssh2_NB_state_idle) {
        session->fullpacket_macstate = LIBSSH2_MAC_CONFIRMED;
        session->fullpacket_payload_len = p->packet_length - 1;

        if (encrypted) {


            session->remote.mac->hash(session, macbuf,
                                      session->remote.seqno,
                                      p->init, 5,
                                      p->payload,
                                      session->fullpacket_payload_len,
                                      &session->remote.mac_abstract);


            if (memcmp(macbuf, p->payload + session->fullpacket_payload_len,
                       session->remote.mac->mac_len)) {
                session->fullpacket_macstate = LIBSSH2_MAC_INVALID;
            }
        }

        session->remote.seqno++;


        session->fullpacket_payload_len -= p->padding_length;


        compressed =
            session->local.comp != NULL &&
            session->local.comp->compress &&
            ((session->state & LIBSSH2_STATE_AUTHENTICATED) ||
             session->local.comp->use_in_auth);

        if (compressed && session->remote.comp_abstract) {


            unsigned char *data;
            size_t data_len;
            rc = session->remote.comp->decomp(session,
                                              &data, &data_len,
                                              LIBSSH2_PACKET_MAXDECOMP,
                                              p->payload,
                                              session->fullpacket_payload_len,
                                              &session->remote.comp_abstract);
            LIBSSH2_FREE(session, p->payload);
            if(rc)
                return rc;

            p->payload = data;
            session->fullpacket_payload_len = data_len;
        }

        session->fullpacket_packet_type = p->payload[0];

        debugdump(session, "libssh2_transport_read() plain",
                  p->payload, session->fullpacket_payload_len);

        session->fullpacket_state = libssh2_NB_state_created;
    }

    if (session->fullpacket_state == libssh2_NB_state_created) {
        rc = _libssh2_packet_add(session, p->payload,
                                 session->fullpacket_payload_len,
                                 session->fullpacket_macstate);
        if (rc == LIBSSH2_ERROR_EAGAIN)
            return rc;
        if (rc) {
            session->fullpacket_state = libssh2_NB_state_idle;
            return rc;
        }
    }

    session->fullpacket_state = libssh2_NB_state_idle;

    return session->fullpacket_packet_type;
}
