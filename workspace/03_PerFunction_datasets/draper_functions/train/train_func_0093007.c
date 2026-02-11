setInteger(const int integer)
{
    ASSERT(this);


    this->clear();
    this->type.setType(DXType::IntegerType);


    this->integer = integer;


    this->string = new char[32];
    sprintf(this->string, "%d", integer);


    return TRUE;
}
