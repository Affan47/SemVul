operator>>(QDataStream &stream, Person::Ptr &person)
{
    QString name, email;
    int count;

    stream >> name >> email >> count;

    Person::Ptr person_tmp(new Person(name, email));
    person_tmp->setCount(count);
    person.swap(person_tmp);
    return stream;
}
