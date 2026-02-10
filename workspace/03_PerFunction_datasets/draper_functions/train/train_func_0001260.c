test_str_xor_normal()
{
    string s1 = "hit the bull's eye";
    string s2 = "the kid don't play";
    string temp = "";
    temp.push_back('\0');
    string expected = "\x1c\x01\x11";
    expected += temp;
    expected += "\x1f\x01\x01";
    expected += temp;
    expected += "\x06\x1a\x02KSSP\t\x18\x1c";
    string got = str_xor(s1, s2);
    if(expected.compare(got) != 0)
    {
        cout << "<<<String XOR Normal Functionality: FAIL>>>" << endl;
        cerr << "Got is: " << got << endl;
        return 0;
    }
    cout << "<<<String XOR Normal Functionality: PASS>>>" << endl;
    return 1;
}
