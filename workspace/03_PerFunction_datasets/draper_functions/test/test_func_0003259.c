encodeName(char g, const string& name)
{
    switch (g) {
        case 'v':
        case 'V': return cons(tree(0), tree(name));

        case 'h':
        case 'H': return cons(tree(1), tree(name));

        case 't':
        case 'T': return cons(tree(2), tree(name));

        default : return cons(tree(0), tree(name));
    }
}
