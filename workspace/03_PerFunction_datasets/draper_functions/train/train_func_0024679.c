AuGetOutputGainAndMode(AuFixedPoint * gainp, AuUint8 * modep)
{
    *gainp = AuCallback(AuGetPhysicalOutputGainCB, ());
    *modep = CallbackExists(AuGetPhysicalOutputModeCB)
            ? AuCallback(AuGetPhysicalOutputModeCB, ())
            : AuDeviceOutputModeSpeaker;
}
