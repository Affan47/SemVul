process_eapol(struct network *n, struct client *c, unsigned char *p,
                          int len, struct ieee80211_frame *wh, int totlen)
{
        int num, i;

        num = eapol_handshake_step(p, len);
        if (num == 0)
                return;


        if (c->c_wpa == 0 || num <= c->c_wpa) {
                for (i = 0; i < 4; i++)
                        c->c_handshake[i].p_len = 0;

                c->c_wpa_got = 0;
        }

        c->c_wpa = num;

        switch (num) {
        case 1:
                c->c_wpa_got |= 1;
                break;

        case 2:
                c->c_wpa_got |= 2;
                c->c_wpa_got |= 4;
                break;

        case 3:
                if (memcmp(&p[17], ZERO, 32) != 0)
                        c->c_wpa_got |= 1;

                c->c_wpa_got |= 4;
                break;

        case 4:
                if (memcmp(&p[17], ZERO, 32) != 0)
                        c->c_wpa_got |= 2;

                c->c_wpa_got |= 4;
                break;

        default:
                abort();
        }

        packet_copy(&c->c_handshake[num - 1], wh, totlen);

        if (c->c_wpa_got == 7)
                n->n_handshake = c;
}
