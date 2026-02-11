gmpc_profiles_get_current (GmpcProfiles * self)
{
#line 934 "gmpc-profiles.c"
#define __GOB_FUNCTION__ "Gmpc:Profiles::get_current"
#line 452 "gmpc-profiles.gob"
	g_return_val_if_fail (self != NULL, (gchar * )0);
#line 452 "gmpc-profiles.gob"
	g_return_val_if_fail (GMPC_IS_PROFILES (self), (gchar * )0);
#line 940 "gmpc-profiles.c"
{
#line 455 "gmpc-profiles.gob"

		gchar *id = cfg_get_single_value_as_string_with_default(config, "connection", "currentprofile", "Default");
		Profile *prof = self_get_profile(self, id);

		if(!prof)
		{
			g_free(id);
            if(self->_priv->list != NULL && self->_priv->list[0])
            {
			    self_set_current(self, self->_priv->list[0]->id);
            } else {
                self_add_default(self);
                self_load_from_config(self);
                self_changed(self, PROFILE_ADDED, -1,"Default");
            }
			id = cfg_get_single_value_as_string_with_default(config, "connection", "currentprofile", "Default");
		}
		return id;
  }}
