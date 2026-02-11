isFallThroughComment(std::string comment)
{

    for (std::string::iterator i = comment.begin(); i != comment.end();) {
        if (std::isspace(static_cast<unsigned char>(*i)))
            i = comment.erase(i);
        else
            ++i;
    }
    std::transform(comment.begin(), comment.end(), comment.begin(), tolowerWrapper);

    return comment.find("fallthr") != std::string::npos ||
           comment.find("fallsthr") != std::string::npos ||
           comment.find("fall-thr") != std::string::npos ||
           comment.find("dropthr") != std::string::npos ||
           comment.find("passthr") != std::string::npos ||
           comment.find("nobreak") != std::string::npos ||
           comment == "fall";
}
