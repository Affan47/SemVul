SetTransformer (Transformer* t) {
    if (_relative != t) {
        Ref(t);
        Unref(_relative);
	_relative = t;
    }
}
