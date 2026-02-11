get(QString name)
{
    NamedSearch returning;
    foreach (NamedSearch x, list) {
        if (x.name == name) {
            returning = x;
            break;
        }
    }
    return returning;
}
