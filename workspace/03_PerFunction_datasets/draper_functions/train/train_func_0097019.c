setPasswordMode(bool b)
{
    if(b)
    {
        KConfigGroup cg(KGlobal::config(), "Passwords");
        const QString val = cg.readEntry("EchoMode", "OneStar");
        if (val == "NoEcho")
            setEchoMode(NoEcho);
        else {
            d->threeStars = (val == "ThreeStars");
            setEchoMode(Password);
        }
    }
    else
    {
        setEchoMode( Normal );
    }
}
