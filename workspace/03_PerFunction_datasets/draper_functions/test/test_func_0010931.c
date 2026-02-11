setupPrinting(CbcModel & model, int modelLogLevel)
{
    if (!modelLogLevel) {
        model.solver()->setHintParam(OsiDoReducePrint, true, OsiHintTry);
        model.messageHandler()->setLogLevel(0);
        model.solver()->messageHandler()->setLogLevel(0);
    } else if (modelLogLevel == 1) {
        model.solver()->setHintParam(OsiDoReducePrint, true, OsiHintTry);
        model.messageHandler()->setLogLevel(1);
        model.solver()->messageHandler()->setLogLevel(0);
    } else {
        model.messageHandler()->setLogLevel(2);
        model.solver()->messageHandler()->setLogLevel(1);
        model.setPrintFrequency(50);
    }
}
