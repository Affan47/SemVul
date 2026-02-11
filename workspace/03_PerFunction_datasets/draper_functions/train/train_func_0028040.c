FindFunction(const char *name) {
        wxString symbol = sci2wx(name);
        if (lib && lib->HasSymbol(symbol)) {
            return static_cast<Function>(lib->GetSymbol(symbol));
        }
        return NULL;
    }
