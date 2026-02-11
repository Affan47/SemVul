lt_ext_module_validate_singleton(char singleton)
{
	return (singleton >= '0' && singleton <= '9') ||
		(singleton >= 'A' && singleton <= 'W') ||
		(singleton >= 'Y' && singleton <= 'Z') ||
		(singleton >= 'a' && singleton <= 'w') ||
		(singleton >= 'y' && singleton <= 'z') ||
		singleton == ' ' ||
		singleton == '*';
}
