insertVariable(const QString &variable)
    {
        if(isCode())
            insert(variable);
        else
            setText(variable);
    }
}
