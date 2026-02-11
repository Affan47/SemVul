compileMultiSignal (Tree L)
{

    L = prepare(L);

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = &input[$0][index];", T(i), xfloat()));
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = &output[$0][index];", T(i), xfloat()));
    }

    fClass->addSharedDecl("fullcount");
    fClass->addSharedDecl("input");
    fClass->addSharedDecl("output");

    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree sig = hd(L);
        fClass->openLoop("count");
        fClass->addExecCode(subst("output$0[i] = $2$1;", T(i), CS(sig), xcast()));
        fClass->closeLoop(sig);
    }

    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
 	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }
}
