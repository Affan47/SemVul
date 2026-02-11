form(const QString &formUid) const
{
    const QList<FormMain*> &roots = d->allEmptyRootForms();
    for(int i=0; i < roots.count(); ++i) {
        Form::FormMain *form = roots.at(i);
        if (form->uuid()==formUid)
            return form;
        const QList<Form::FormMain*> &children = form->flattenedFormMainChildren();
        for(int j=0; j < children.count(); ++j) {
            Form::FormMain *test = children.at(j);
            if (test->uuid()==formUid)
                return test;
        }
    }
    return 0;
}
