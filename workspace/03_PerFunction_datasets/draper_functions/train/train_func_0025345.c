GC_unregister(const VALUE& obj) {
      if (FIXNUM_P(obj) || SPECIAL_CONST_P(obj) || SYMBOL_P(obj))
        return;


      if (BUILTIN_TYPE(obj) == T_NONE)
        return;
      if (_hash != Qnil) {
        VALUE val = rb_hash_aref(s_references._hash, obj);
        unsigned n = FIXNUM_P(val) ? NUM2UINT(val) : 1;
        --n;
        if (n)
          rb_hash_aset(s_references._hash, obj, INT2NUM(n));
        else
          rb_hash_delete(s_references._hash, obj);
      }
    }
