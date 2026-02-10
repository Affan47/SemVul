backsql_delete_attr_f( void *v_at, void *v_bda )
{
	backsql_at_map_rec	*at = (backsql_at_map_rec *)v_at;
	backsql_delete_attr_t	*bda = (backsql_delete_attr_t *)v_bda;
	int			rc;

	rc = backsql_modify_delete_all_values( bda->op,
			bda->rs, bda->dbh, bda->e_id, at );

	if ( rc != LDAP_SUCCESS ) {
		return BACKSQL_AVL_STOP;
	}

	return BACKSQL_AVL_CONTINUE;
}
