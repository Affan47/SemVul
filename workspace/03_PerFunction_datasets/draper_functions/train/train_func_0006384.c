Cone_Volume(float baseradius, float height, bool show_work)
{
        float volume;
        volume = ((M_PI * pow(baseradius, 2)) * height) /3;
        if (show_work == false)
        {
            cout << "Volume = ((Pi * " << baseradius << " squared) * " << height << ")/3 " << endl;
            cout << "Volume = ((Pi * " << pow(baseradius, 2) << ") * " << height << ")/3 " << endl;
            cout << "Volume = (" << M_PI * pow(baseradius, 2) << " * " << height << ")/3" << endl;
            cout << "Volume = " << ((M_PI * pow(baseradius, 2)) * height) << " /3" << endl;
            cout << "Volume = " << ((M_PI * pow(baseradius, 2)) * height)/3 << endl << endl;
        }
        return volume;
}
