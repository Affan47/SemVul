beginAnd()
{
    d->queryFilter += andOr();
    d->queryFilter += " ( 1 ";
    d->andStack.push( true );
    return this;
}
