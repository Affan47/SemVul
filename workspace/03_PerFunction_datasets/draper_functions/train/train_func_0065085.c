IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plScaleValueController") {
        if (!tag->getParam("NULL", "false").toBool()) {
            setValue(new plScaleValueController());
            fValue->prcParse(tag, mgr);
        } else {
            setValue(NULL);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
