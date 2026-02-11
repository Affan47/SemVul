il4965_restore_default_wep_keys(struct il_priv *il)
{
	lockdep_assert_held(&il->mutex);

	return il4965_static_wepkey_cmd(il, false);
}
