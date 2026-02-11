sl_derivative(lua_State * L)
{
    const struct syslinux_version *sv;

    sv = syslinux_version();

    switch (sv->filesystem) {
    case SYSLINUX_FS_SYSLINUX:
	lua_pushstring(L, "SYSLINUX");
	break;
    case SYSLINUX_FS_PXELINUX:
	lua_pushstring(L, "PXELINUX");
	break;
    case SYSLINUX_FS_ISOLINUX:
	lua_pushstring(L, "ISOLINUX");
	break;
    case SYSLINUX_FS_UNKNOWN:
    default:
	lua_pushstring(L, "Unknown Syslinux derivative");
	break;
    }

    return 1;
}
