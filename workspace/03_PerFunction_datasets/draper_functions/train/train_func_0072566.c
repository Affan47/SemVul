message_len(char* message_string){
    int i;
    int overflow = 1;

    for(i = 0; i < MESSAGE_SIZE; i++){
        if (message_string[i] == '\0'){
            overflow = 0;
            break;
        }
    }
    if (overflow){
        return ERROR_MAX_STRING_LENGTH;
    }
    else{
        return i;
    }
}
