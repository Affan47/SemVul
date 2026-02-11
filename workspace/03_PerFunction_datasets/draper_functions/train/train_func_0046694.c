compareVal( QStringRef compare )
{
    if( compare == "less" )
        return Collections::QueryMaker::LessThan;
    else if( compare == "greater" )
        return Collections::QueryMaker::GreaterThan;
    else if( compare == "equals" )
        return Collections::QueryMaker::Equals;
    else
        return -1;
}
