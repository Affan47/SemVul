WriteVal(std::ostream &s){
    tConfItem<tString>::WriteVal(s);


    if ( target->Len() >= 2 &&
            target->operator()(target->Len() - 2) == '\\' )
        s << "\\";
}
