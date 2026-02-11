simplifyPath(const char *originalPath)
{
    std::string subPath = "";
    std::vector<std::string> pathParts;
    for (; *originalPath; ++originalPath)
    {
        if (*originalPath == '/' || *originalPath == '\\')
        {
            if (subPath.length() > 0)
            {
                pathParts.push_back(subPath);
                subPath = "";
            }

            pathParts.push_back(std::string(1 , *originalPath));
        }
        else
            subPath.append(1, *originalPath);
    }

    if (subPath.length() > 0)
        pathParts.push_back(subPath);

    for (unsigned int i = 0; i < pathParts.size(); ++i)
    {
        if (i > 1 && pathParts[i-2] != ".." && pathParts[i] == ".." && pathParts.size() > i + 1)
        {
            pathParts.erase(pathParts.begin() + static_cast<int>(i) + 1);
            pathParts.erase(pathParts.begin() + static_cast<int>(i));
            pathParts.erase(pathParts.begin() + static_cast<int>(i) - 1);
            pathParts.erase(pathParts.begin() + static_cast<int>(i) - 2);
            i = 0;
        }
        else if (i > 0 && pathParts[i] == ".")
        {
            pathParts.erase(pathParts.begin() + static_cast<int>(i));
            i = 0;
        }
        else if (pathParts[i] == "/" && i > 0 && pathParts[i-1] == "/")
        {
            pathParts.erase(pathParts.begin() + static_cast<int>(i) - 1);
            i = 0;
        }
    }

    std::ostringstream oss;
    for (std::vector<std::string>::size_type i = 0; i < pathParts.size(); ++i)
    {
        oss << pathParts[i];
    }

    return oss.str();
}
