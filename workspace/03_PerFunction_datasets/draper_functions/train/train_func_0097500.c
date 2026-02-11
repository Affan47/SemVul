SaveAll(std::ostream &s){
    tConfItemMap & confmap = ConfItemMap();
    for(tConfItemMap::iterator iter = confmap.begin(); iter != confmap.end() ; ++iter)
    {
        tConfItemBase * ci = (*iter).second;
        if (ci->Save()){
            s << std::setw(28) << ci->title << " ";
            ci->WriteVal(s);
            s << '\n';
        }
    }
}
