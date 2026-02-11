IPrcWrite(pfPrcHelper* prc) {
    plEAXEffect::IPrcWrite(prc);

    prc->writeSimpleTag("SoftRegion");
    fSoftRegion->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("ReverbProperties");
    prc->startTag("EAXREVERBPROPERTIES");
    prc->writeParam("Environment", fListenerProps.ulEnvironment);
    prc->writeParam("EnvironmentSize", fListenerProps.flEnvironmentSize);
    prc->writeParam("EnvironmentDiffusion", fListenerProps.flEnvironmentDiffusion);
    prc->writeParam("Room", fListenerProps.lRoom);
    prc->writeParam("RoomHF", fListenerProps.lRoomHF);
    prc->writeParam("RoomLF", fListenerProps.lRoomLF);
    prc->writeParam("DecayTime", fListenerProps.flDecayTime);
    prc->writeParam("DecayHFRatio", fListenerProps.flDecayHFRatio);
    prc->writeParam("DecayLFRatio", fListenerProps.flDecayLFRatio);
    prc->writeParam("Reflections", fListenerProps.lReflections);
    prc->writeParam("ReflectionsDelay", fListenerProps.flReflectionsDelay);
    prc->writeParam("Reverb", fListenerProps.lReverb);
    prc->writeParam("ReverbDelay", fListenerProps.flReverbDelay);
    prc->writeParam("EchoTime", fListenerProps.flEchoTime);
    prc->writeParam("EchoDepth", fListenerProps.flEchoDepth);
    prc->writeParam("ModulationTime", fListenerProps.flModulationTime);
    prc->writeParam("ModulationDepth", fListenerProps.flModulationDepth);
    prc->writeParam("AirAbsorptionHF", fListenerProps.flAirAbsorptionHF);
    prc->writeParam("HFReference", fListenerProps.flHFReference);
    prc->writeParam("LFReference", fListenerProps.flLFReference);
    prc->writeParam("RoomRolloffFactor", fListenerProps.flRoomRolloffFactor);
    prc->writeParamHex("Flags", fListenerProps.ulFlags);
    prc->endTag(true);
    prc->closeTag();

    prc->writeSimpleTag("Apertures");
    for (size_t i = 0; i < fApertures.getSize(); i++) {
        prc->writeSimpleTag("Aperture");
        fApertures[i].fX.prcWrite(prc);
        fApertures[i].fY.prcWrite(prc);
        fApertures[i].fZ.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}
