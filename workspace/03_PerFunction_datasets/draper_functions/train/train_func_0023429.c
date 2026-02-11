write_return_code(divas_um_idi_entity_t *e, byte rc)
{
	diva_um_idi_ind_hdr_t *prc;

	if (!(prc =
	      (diva_um_idi_ind_hdr_t *) diva_data_q_get_segment4write(&e->rc)))
	{
		DBG_ERR(("A: A(%d) E(%08x) rc(%02x) lost",
			 e->adapter->adapter_nr, e, rc));
		e->status &= ~DIVA_UM_IDI_RC_PENDING;
		return (-1);
	}

	prc->type = DIVA_UM_IDI_IND_RC;
	prc->hdr.rc.Rc = rc;
	prc->hdr.rc.RcCh = e->e.RcCh;
	prc->data_length = 0;
	diva_data_q_ack_segment4write(&e->rc, sizeof(*prc));

	return (0);
}
