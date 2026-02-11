auth_password(ssh_session session, const char *user,
        const char *password, void *userdata){

    (void)userdata;

    printf("Authenticating user %s pwd %s\n",user, password);
    if(strcmp(user,USER) == 0 && strcmp(password, PASSWORD) == 0){
        authenticated = 1;
        printf("Authenticated\n");
        return SSH_AUTH_SUCCESS;
    }
    if (tries >= 3){
        printf("Too many authentication tries\n");
        ssh_disconnect(session);
        error = 1;
        return SSH_AUTH_DENIED;
    }
    tries++;
    return SSH_AUTH_DENIED;
}
