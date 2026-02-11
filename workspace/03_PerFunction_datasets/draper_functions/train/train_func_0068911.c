eval() {
    char exprbuf[BUFSIZ];
    const char* expr = expredit_->text();
    if (expr[strlen(expr)-1] != '\n')
        sprintf(exprbuf, "%s\n", expr);
    else
        sprintf(exprbuf, "%s", expr);

    ComValue retval(terpserv_->run(exprbuf));

    const char* errmsg = terpserv_->errmsg();
    if (*errmsg) {
        result_->textvalue("");
        err_->textvalue(errmsg);
    } else if (retval.type() == ComValue::UnknownType) {
        result_->textvalue("nil");
        err_->textvalue("");
    } else {
        char buf[BUFSIZ];
        buf[0] = '\0';
        std::ostrstream ostr(buf, BUFSIZ);

        ostr << retval;
	ostr << '\0';

        result_->textvalue(buf);
        err_->textvalue("");
    }

    resultview_->update(result_);
    errview_->update(err_);

}
