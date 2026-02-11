substitute_variable_in_string (const std::string& variable_name, std::string& filepath) const
{
    std::string variable_token = "${" + variable_name + "}";

    for (std::string::size_type pos = filepath.find (variable_token);
         pos != std::string::npos;
         pos = filepath.find (variable_token, pos))
    {
        const char* value = getenv(variable_name.c_str());
        if (value)
        {
            filepath.replace (pos,
                              variable_token.size(),
                              value);
        }
        else
        {

	    if (variable_name == "HOME")
	    {
		value = getenv("USERPROFILE");
		if (value)
		{
		    filepath.replace (pos,
				      variable_token.size(),
				      value);
		}
	    }
	    else
	    {


		filepath.replace (pos,
				  variable_token.size(),
				  variable_name);
	    }
	}
    }
}
