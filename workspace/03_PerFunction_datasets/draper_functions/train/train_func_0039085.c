remove(ParmStr s) {
        Value c = *(Value *)conv(s);
        Vector<Value>::iterator i = data.begin();
        Vector<Value>::iterator end = data.end();
        for (; i != end && *i != c; ++i);
        if (i != end) data.erase(i);
        return true;
      }
