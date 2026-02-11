getValueProperty(ExecState* , int token) const
{
    switch (token)
    {
        case Top:
            return jsNumber(top());
        case Right:
            return jsNumber(right());
        case Left:
            return jsNumber(left());
        case Bottom:
            return jsNumber(bottom());
        case Height:
            return jsNumber(height());
        case Width:
            return jsNumber(width());
    }
    return jsUndefined();
}
