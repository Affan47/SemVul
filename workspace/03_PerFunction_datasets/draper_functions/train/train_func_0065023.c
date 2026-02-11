registerTest(TestMethod* test)
{
    test->setParent(this);
    std::pair<const std::string, TestMethod*> p( test->name(), test );
    _tests.push_back( p );
}


}
