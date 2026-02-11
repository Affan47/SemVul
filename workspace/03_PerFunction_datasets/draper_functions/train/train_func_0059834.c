IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Root");
    fRoot->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Wheels");
    for (size_t i=0; i<4; i++) {
        prc->startTag("Wheel");
        prc->writeParam("Radius", fWheels[i].fRadius);
        prc->endTag();
          fWheels[i].fWheelObj->prcWrite(prc);
          prc->writeSimpleTag("Position");
          fWheels[i].fPosition.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Direction");
          fWheels[i].fDirection.prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();
}
