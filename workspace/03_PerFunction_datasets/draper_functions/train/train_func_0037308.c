remove(const string key)


{

    modelMap::iterator it = mapModels.find(key);
    if ( key.empty() || it == mapModels.end() ) {
        cerr << "ERROR: Indexed::remove() Invalid Key" << endl;
        return false;
    } else {
        mapModels.erase(it);
        this->n--;
        return true;
    }
}
