dumpCode() const {
	for(size_t i = 0; i < ir.size(); i++) {
		std::cout << ByteCode::toString(ir[i].bc) << "\t" << ir[i].a.toString() << "\t" << ir[i].b.toString() << "\t" << ir[i].c.toString() << std::endl;
	}
}
