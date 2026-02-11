gmpc_profiles_free_profile (Profile * profile)
{
#line 505 "gmpc-profiles.c"
#define __GOB_FUNCTION__ "Gmpc:Profiles::free_profile"
{
#line 188 "gmpc-profiles.gob"

    if(profile->name)
      g_free(profile->name);
    if(profile->id)
      g_free(profile->id);
    if(profile->hostname)
      g_free(profile->hostname);
    if(profile->password)
      g_free(profile->password);
    if(profile->music_directory)
        g_free(profile->music_directory);

    profile->db_update_time = 0;
    g_free(profile);
  }}
