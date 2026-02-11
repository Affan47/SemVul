request_and_encrypt_pin(pam_handle_t  *handle,
                        const char    *username,
                        char         **ciphertext,
                        size_t        *ciphertext_len)
{
        const char *password;
        char *pin;
        int result;

        *ciphertext = NULL;

        result = pam_get_authtok (handle, PAM_AUTHTOK, &password, "Password: ");
        if (result != PAM_SUCCESS)
                return result;

        result = pam_prompt (handle, PAM_PROMPT_ECHO_OFF, &pin, "PIN");
        if (result != PAM_SUCCESS)
                return result;

        if (pin == NULL || strlen (pin) == 0) {
                result = PAM_SUCCESS;
        } else {
                *ciphertext = encode_password (password, pin, ciphertext_len);
                if (!*ciphertext)
                        result = PAM_AUTHTOK_ERR;
                else
                        result = PAM_SUCCESS;
        }


        free(pin);
        return result;
}
