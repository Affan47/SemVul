lightdm_greeter_authenticate_autologin (LightDMGreeter *greeter)
{
    const gchar *user;

    user = lightdm_greeter_get_autologin_user_hint (greeter);
    if (lightdm_greeter_get_autologin_guest_hint (greeter))
        lightdm_greeter_authenticate_as_guest (greeter);
    else if (user)
        lightdm_greeter_authenticate (greeter, user);
}
