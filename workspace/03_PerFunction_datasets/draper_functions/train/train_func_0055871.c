ReadVal(std::istream &s){
    tString dummy;
    dummy.ReadLine(s, true);
    if(strcmp(dummy,*target)){
        if (printChange)
        {
            tColoredString oldval;
            oldval << *target << tColoredString::ColorString(1,1,1);
            tColoredString newval;
            newval << dummy << tColoredString::ColorString(1,1,1);
            tOutput o;
            o.SetTemplateParameter(1, title);
            o.SetTemplateParameter(2, oldval);
            o.SetTemplateParameter(3, newval);
            o << "$config_value_changed";
            con << o;
        }
        *target=dummy;
        changed=true;
    }

    *target=dummy;
}
