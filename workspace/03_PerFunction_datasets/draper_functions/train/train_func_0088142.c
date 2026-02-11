errorContext(const char* log_message, std::string& context) {

    std::vector<std::string> matches;

    if(   !Shader_error_line.match(log_message, &matches)
       && !Shader_error2_line.match(log_message, &matches)
       && !Shader_error3_line.match(log_message, &matches)
       && !(Logger::getDefault()->getLevel() == LOG_LEVEL_WARN && Shader_warning_line.match(log_message, &matches)))
        return false;

    int line_no = atoi(matches[0].c_str());

    if(Shader_redefine_line.match(log_message, &matches)) {
        int redefine_line_no = atoi(matches[0].c_str());
        showContext(context, redefine_line_no, 3);
        context += "\n";
    }

    showContext(context, line_no, 3);

    return true;
}
