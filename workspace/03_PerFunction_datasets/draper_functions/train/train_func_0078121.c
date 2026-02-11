addRaw2Interactions(std::istream &iStream)
    {
      Raw2InteractionReader reader(iStream);
      ContactCollection contacts;
      contacts.addInteractions(reader);

      m_stressTensorCollection.addContactIterators(contacts.getContactIteratorIterator());
    }
