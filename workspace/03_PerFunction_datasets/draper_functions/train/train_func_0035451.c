pk_role_enum_to_localised_present (PkRoleEnum role)
{
	const gchar *text = NULL;
	switch (role) {
	case PK_ROLE_ENUM_UNKNOWN:

		text = dgettext("PackageKit", "Unknown role type");
		break;
	case PK_ROLE_ENUM_GET_DEPENDS:

		text = dgettext("PackageKit", "Getting dependencies");
		break;
	case PK_ROLE_ENUM_GET_UPDATE_DETAIL:

		text = dgettext("PackageKit", "Getting update details");
		break;
	case PK_ROLE_ENUM_GET_DETAILS:

		text = dgettext("PackageKit", "Getting details");
		break;
	case PK_ROLE_ENUM_GET_REQUIRES:

		text = dgettext("PackageKit", "Getting requires");
		break;
	case PK_ROLE_ENUM_GET_UPDATES:

		text = dgettext("PackageKit", "Getting updates");
		break;
	case PK_ROLE_ENUM_SEARCH_DETAILS:

		text = dgettext("PackageKit", "Searching by details");
		break;
	case PK_ROLE_ENUM_SEARCH_FILE:

		text = dgettext("PackageKit", "Searching by file");
		break;
	case PK_ROLE_ENUM_SEARCH_GROUP:

		text = dgettext("PackageKit", "Searching groups");
		break;
	case PK_ROLE_ENUM_SEARCH_NAME:

		text = dgettext("PackageKit", "Searching by name");
		break;
	case PK_ROLE_ENUM_REMOVE_PACKAGES:

		text = dgettext("PackageKit", "Removing");
		break;
	case PK_ROLE_ENUM_INSTALL_PACKAGES:

		text = dgettext("PackageKit", "Installing");
		break;
	case PK_ROLE_ENUM_INSTALL_FILES:

		text = dgettext("PackageKit", "Installing files");
		break;
	case PK_ROLE_ENUM_REFRESH_CACHE:

		text = dgettext("PackageKit", "Refreshing cache");
		break;
	case PK_ROLE_ENUM_UPDATE_PACKAGES:

		text = dgettext("PackageKit", "Updating packages");
		break;
	case PK_ROLE_ENUM_CANCEL:

		text = dgettext("PackageKit", "Canceling");
		break;
	case PK_ROLE_ENUM_GET_REPO_LIST:

		text = dgettext("PackageKit", "Getting repositories");
		break;
	case PK_ROLE_ENUM_REPO_ENABLE:

		text = dgettext("PackageKit", "Enabling repository");
		break;
	case PK_ROLE_ENUM_REPO_SET_DATA:

		text = dgettext("PackageKit", "Setting data");
		break;
	case PK_ROLE_ENUM_RESOLVE:

		text = dgettext("PackageKit", "Resolving");
		break;
	case PK_ROLE_ENUM_GET_FILES:

		text = dgettext("PackageKit", "Getting file list");
		break;
	case PK_ROLE_ENUM_WHAT_PROVIDES:

		text = dgettext("PackageKit", "Getting provides");
		break;
	case PK_ROLE_ENUM_INSTALL_SIGNATURE:

		text = dgettext("PackageKit", "Installing signature");
		break;
	case PK_ROLE_ENUM_GET_PACKAGES:

		text = dgettext("PackageKit", "Getting packages");
		break;
	case PK_ROLE_ENUM_ACCEPT_EULA:

		text = dgettext("PackageKit", "Accepting EULA");
		break;
	case PK_ROLE_ENUM_DOWNLOAD_PACKAGES:

		text = dgettext("PackageKit", "Downloading packages");
		break;
	case PK_ROLE_ENUM_GET_DISTRO_UPGRADES:

		text = dgettext("PackageKit", "Getting upgrades");
		break;
	case PK_ROLE_ENUM_GET_CATEGORIES:

		text = dgettext("PackageKit", "Getting categories");
		break;
	case PK_ROLE_ENUM_GET_OLD_TRANSACTIONS:

		text = dgettext("PackageKit", "Getting transactions");
		break;
	default:
		g_warning ("role unrecognised: %s", pk_role_enum_to_string (role));
	}
	return text;
}
