key() const

{
    ostringstream out;
    out << Config::CAT_FICTION << this->author << this->title;
    return out.str();
}
