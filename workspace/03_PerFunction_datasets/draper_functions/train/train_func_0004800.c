VRT_l_req_esi(const struct sess *sp, unsigned process_esi)
{
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);


	if(sp->req->esi_level == 0)
		sp->req->disable_esi = !process_esi;
}
