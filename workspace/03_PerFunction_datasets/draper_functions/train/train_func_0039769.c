Connection_getInsertId(CTX ctx, ksfp_t *sfp _RIX)
{
	kConnection *c = (kConnection*)sfp[0].o;
	RETURNi_((kuint_t)mysql_insert_id((MYSQL*)c->conn));
}
