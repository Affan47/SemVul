tcp_state(int state)
{
    switch (state)
    {
    case TOKEN_WELCOME : {
            label->setText("Connecting to remote server...");
            break;
        }
    case RSA_PUBLIC_KEY_RECEPTION : {
            label->setText("RSA asymetric encryption started...");
            break;
        }
    case PASSWORD_VALIDATION : {
            label->setText("Password validation process...");
            break;
        }
    case AES_KEY_RECEPTION : {
            label->setText("AES symetric encryption started...");
            break;
        }
    case AUTH_SUCCESS : {
            label->setText("Authentication succeded. AES symetric encryption started...");
            progress->hide();
            label->hide();
            break;
        }
    default:
        ;
    }
}
