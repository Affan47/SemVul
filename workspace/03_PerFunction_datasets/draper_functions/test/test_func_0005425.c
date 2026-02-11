FindAddModel(trpgModel &mod)
{

    ModelMapType::iterator itr = modelsMap.begin();
    for (  ; itr != modelsMap.end( ); itr++) {
        if(itr->second == mod) {
            return itr->first;
        }
    }
    return AddModel(mod);
}
