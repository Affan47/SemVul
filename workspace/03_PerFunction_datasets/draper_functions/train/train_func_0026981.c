indexGetter(ExecState* exec, unsigned index)
{
    Q_UNUSED(exec);
    if (index >= size)
        return jsNull();

    unsigned pixel = index / 4;
    unsigned comp  = index % 4;
    QColor color = parent->impl()->pixel(pixel);

    switch (comp) {
    case 0: return jsNumber(color.red());
    case 1: return jsNumber(color.green());
    case 2: return jsNumber(color.blue());
    default:
            return jsNumber(color.alpha());
    }
}
