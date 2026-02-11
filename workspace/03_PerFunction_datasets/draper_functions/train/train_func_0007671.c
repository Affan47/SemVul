relative_system_support_dir()
{
	string result;

#if defined (USE_WINDOWS_PACKAGING) || defined (USE_MACOSX_PACKAGING)
	result = "../Resources/";
#else
	result = addPath("../share/", PACKAGE);
#endif

	return result;
}

}
