ctags_visitor_real_visit_source_file (ValaCodeVisitor* base, ValaSourceFile* source_file) {
	CTagsVisitor * self;
	ValaSourceFile* _tmp0_;
#line 155 "/tmp/buildd/anjuta-3.10.2/plugins/symbol-db/anjuta-tags/ctags-visitor.vala"
	self = (CTagsVisitor*) base;
#line 155 "/tmp/buildd/anjuta-3.10.2/plugins/symbol-db/anjuta-tags/ctags-visitor.vala"
	g_return_if_fail (source_file != NULL);
#line 156 "/tmp/buildd/anjuta-3.10.2/plugins/symbol-db/anjuta-tags/ctags-visitor.vala"
	_tmp0_ = source_file;
#line 156 "/tmp/buildd/anjuta-3.10.2/plugins/symbol-db/anjuta-tags/ctags-visitor.vala"
	vala_source_file_accept_children (_tmp0_, (ValaCodeVisitor*) self);
#line 1377 "ctags-visitor.c"
}
