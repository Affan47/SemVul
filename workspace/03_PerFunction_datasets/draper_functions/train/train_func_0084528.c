VRT_r_req_backend_healthy(const struct sess *sp)
{
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->req->director, DIRECTOR_MAGIC);
	return (VDI_Healthy(sp->req->director, sp));
}
