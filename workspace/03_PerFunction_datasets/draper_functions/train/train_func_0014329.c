setAverageFromText(const QString text) {
    int value = text.toDouble();
    averageEdit->setText(text);
    if (average != value) {
        average = value;
        averageSlider->setValue(average);


        sum = 0;
        int j = index-(count<average*5?count:average*5);
        for (int i=0; i<average*5; i++)  {
            sum += rolling[(j>=0?j:150+j)];
            j++;
        }
    }
}
