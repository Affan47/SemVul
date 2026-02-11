profile_flush(profile_t profile)
{
    if (!profile || profile->magic != PROF_MAGIC_PROFILE)
        return PROF_MAGIC_PROFILE;

    if (profile->vt) {
        if (profile->vt->flush)
            return profile->vt->flush(profile->cbdata);
        return 0;
    }

    if (profile->first_file)
        return profile_flush_file(profile->first_file);

    return 0;
}
