print(ostream& out) const

{
    out << endl
        << "*** Patron ID = "
        << right
        << setfill('0') << setw(4)
        << this->getID()
        << " "
        << this->getFirstName()
        << " "
        << this->getLastName()
        << endl;
}
