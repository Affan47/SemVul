add_no_work_message(const char* message) {
    for (unsigned int i=0; i<no_work_messages.size(); i++) {
        if (!strcmp(message, no_work_messages.at(i).message.c_str())){
            return;
        }
    }
    no_work_messages.push_back(USER_MESSAGE(message, "notice"));
}
