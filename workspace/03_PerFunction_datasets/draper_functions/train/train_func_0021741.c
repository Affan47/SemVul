operator()(const as_value& val) {
        VM& vm = getVM(_fn);

        newAdd(_ret, "<property id=\"", vm);
        newAdd(_ret, static_cast<double>(_count), vm);
        newAdd(_ret, "\">", vm);
        as_object* ei =
            findObject(_fn.env(), "flash.external.ExternalInterface");
        const as_value& x = callMethod(ei, getURI(vm, "_toXML"), val);
        newAdd(_ret, x, vm);
        newAdd(_ret, "</property>", vm);
        ++_count;
    }
