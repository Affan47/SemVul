slotInstallationVerification(int result)
{


    if (result & Security::SIGNED_OK)
        emit signalInstallationFinished();
    else
        emit signalInstallationFailed();
}
