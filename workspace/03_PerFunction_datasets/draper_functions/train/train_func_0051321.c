ColouriseTADS3LibDirective(StyleContext &sc, int &lineState) {
        int initState = sc.state;
        int chQuote = '"';
        switch (initState) {
                case SCE_T3_S_STRING:
                        sc.SetState(SCE_T3_LIB_DIRECTIVE);
                        sc.Forward(2);
                        chQuote = '\'';
                        break;
                case SCE_T3_D_STRING:
                        sc.SetState(SCE_T3_LIB_DIRECTIVE);
                        sc.Forward(2);
                        break;
                case SCE_T3_LIB_DIRECTIVE:
                        if (lineState&T3_SINGLE_QUOTE) {
                                initState = SCE_T3_S_STRING;
                                chQuote = '\'';
                        } else {
                                initState = SCE_T3_D_STRING;
                        }
                        break;
        }
        while (sc.More() && IsADirectiveChar(sc.ch)) {
                if (IsEOL(sc.ch, sc.chNext)) {
                        return;
                }
                sc.Forward();
        };
        if (sc.ch == '>' || !sc.More()) {
                sc.ForwardSetState(initState);
        } else if (sc.ch == chQuote) {
                sc.SetState(initState);
        } else {
                sc.ChangeState(initState);
                sc.Forward();
        }
}
